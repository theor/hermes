#pragma once

#include <Arduino.h>
#include "sync.h"


#define sizeof_array(array) (int)(sizeof(array) / sizeof(array[0]))
#define ROCKET_HOST_IP "10.0.0.25"
static const char *s_trackNames[] = {
    "can#X",
    "can#Y",
    "flower#stem",
    "flower#open",
    "heart#X",
    "heart#Y",
};

static struct sync_device *device;
static const struct sync_track *s_tracks[7];
const float bpm = 180.0f;
const float rpb = 8.0f;
float rps = 24.0f; // bpm / 60.0f * rpb; <- msvc cant compute this compile time... sigh

int audio_is_playing = 1;
int curtime_ms = 0;

#if !defined(SYNC_PLAYER)
static struct sync_cb cb;
#endif


#if !defined(SYNC_PLAYER)


static int row_to_ms_round(int row, float rps)
{
  const float newtime = ((float)(row)) / rps;
  return (int)(floor(newtime * 1000.0f + 0.5f));
}

static float ms_to_row_f(int time_ms, float rps)
{
  const float row = rps * ((float)time_ms) * 1.0f / 1000.0f;
  return row;
}


static int ms_to_row_round(int time_ms, float rps)
{
  const float r = ms_to_row_f(time_ms, rps);
  return (int)(floor(r + 0.5f));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void xpause(void *data, int flag)
{
  (void)data;
  Serial.print("pause ");
  Serial.println(flag);

  if (flag)
    audio_is_playing = 0;
  else
    audio_is_playing = 1;
}

static void xset_row(void *data, int row)
{
//   Serial.print("set row ");
//   Serial.println(row);
  int newtime_ms = row_to_ms_round(row, rps);
  curtime_ms = newtime_ms;
  (void)data;
}

static int xis_playing(void *data)
{
  (void)data;
  return audio_is_playing;
}

#endif //! SYNC_PLAYER

int rocket_init(const char *prefix)
{
  device = sync_create_device(prefix);
  if (!device)
  {
    Serial.println("Unable to create rocketDevice\n");
    return 0;
  }

#if !defined(SYNC_PLAYER)
  cb.is_playing = xis_playing;
  cb.pause = xpause;
  cb.set_row = xset_row;

  if (sync_tcp_connect(device, ROCKET_HOST_IP, SYNC_DEFAULT_PORT))
  {
    Serial.println("Rocket failed to connect\n");
    free(device);
    device = nullptr;
    return 0;
  }
#endif

  Serial.println("Rocket connected.\n");

  return 1;
}


static int rocket_update()
{
  int row = 0;

  if (audio_is_playing)
    curtime_ms += 16; //...60hz or gtfo

#if !defined(SYNC_PLAYER)
  row = ms_to_row_round(curtime_ms, rps);
  if (sync_update(device, row, &cb, 0))
    sync_tcp_connect(device, ROCKET_HOST_IP, SYNC_DEFAULT_PORT);
#endif

  return 1;
}