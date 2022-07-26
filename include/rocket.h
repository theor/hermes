#pragma once

#include <Arduino.h>
#include "sync.h"
#include "global.h"

#ifndef SIMULATOR
#include <SPIFFS.h>
#endif


#define sizeof_array(array) (int)(sizeof(array) / sizeof(array[0]))
#define ROCKET_HOST_IP "10.0.0.25"

static struct sync_device *device;
// const float bpm = 180.0f;
// const float rpb = 8.0f; // row per beat
// float rps = 24.0f; // row per second bpm / 60.0f * rpb; <- msvc cant compute this compile time... sigh
const int rps = 10;

int audio_is_playing = 1;
int curtime_ms = 0;

#if !defined(SYNC_PLAYER)
static struct sync_cb cb;
#endif


// static float ms_to_row_f(int time_ms, float rps, const struct sync_track *loop_track )
// {
//   const float row = rps * ((float)time_ms) * 1.0f / 1000.0f;
//   if(loop_track) {
//       float loopDelta = (float)sync_get_val(loop_track, row);
//       if(loopDelta > 0.1f)
//         return row - loopDelta;
//   }
//   return row;
// }
#if !defined(SYNC_PLAYER)


// static int row_to_ms_round(int row, float rps)
// {
//   const float newtime = ((float)(row)) / rps;
//   return (int)(floor(newtime * 1000.0f + 0.5f));
// }



// static int ms_to_row_round(int time_ms, float rps, const struct sync_track *loop_track)
// {
//   const float r = ms_to_row_f(time_ms, rps, loop_track);
//   return (int)(floor(r + 0.5f));
// }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void xpause(void *data, int flag) {
    (void) data;
    Serial.print("pause ");
    Serial.println(flag);

    if (flag)
        audio_is_playing = 0;
    else
        audio_is_playing = 1;
}

static void xset_row(void *data, int row) {
//   Serial.print("set row ");
//   Serial.println(row);
    int newtime_ms = row * 1000 / rps;
    curtime_ms = newtime_ms;
    (void) data;
}

static int xis_playing(void *data) {
    (void) data;
    return audio_is_playing;
}

#endif //! SYNC_PLAYER

#ifndef SIMULATOR
void *io_open(const char *filename, const char *mode) {
    Serial.println(String("open ") + filename + " " + mode);
    String sFilename('/');
    sFilename += filename;
    if (sFilename.length() >= 31)
        sFilename = sFilename.substring(0, 30);

    fs::File *stream = new fs::File(SPIFFS.open(sFilename, mode));
    return stream;
}

size_t io_read(void *ptr, size_t size, size_t nitems, void *stream) {
    Serial.println(String("read ") + size * nitems);
    return ((fs::File *) stream)->readBytes((char *) ptr, size * nitems);
}

size_t io_write(const void *ptr, const size_t size, const size_t nitems, void *stream) {
    Serial.println(String("write ") + size * nitems + ((fs::File *) stream)->name());
    return ((fs::File *) stream)->write((uint8_t *) ptr, size * nitems);
}

int io_close(void *stream) {
    Serial.println("close");
    ((fs::File *) stream)->close();
    delete ((fs::File *) stream);
    return 0;
}
#endif
int rocket_init() {
    device = sync_create_device(nullptr);
    if (!device) {
        Serial.println("Unable to create rocketDevice\n");
        return 0;
    }
    sync_io_cb iocb;
#ifndef SIMULATOR
    iocb.open = &io_open;
    iocb.read = &io_read;
#if !defined(SYNC_PLAYER)
    iocb.write = &io_write;
#endif
    iocb.close = &io_close;
    sync_set_io_cb(device, &iocb);
#endif

#if !defined(SYNC_PLAYER)
    cb.is_playing = xis_playing;
    cb.pause = xpause;
    cb.set_row = xset_row;

//  if (sync_tcp_connect(device, ROCKET_HOST_IP, SYNC_DEFAULT_PORT))
//  {
//    Serial.println("Rocket failed to connect\n");
//    free(device);
//    device = nullptr;
//    return 0;
//  }
    Serial.println("Rocket connected.\n");
#else
    Serial.println("Rocket player initialized.\n");
#endif


    return 1;
}

static int rocket_update() {
    int row = 0;
    row = curtime_ms * rps / 1000;// ms_to_row_round(curtime_ms, rps, nullptr);
//    Serial.println("wifi ?");
    if (WiFi.isConnected())
    {
//        Serial.println("  wifi");
        if (sync_update(device, row, &cb, 0) && debugMode)
        {
            Serial.println("    reconnect rocket");
            sync_tcp_connect(device, ROCKET_HOST_IP, SYNC_DEFAULT_PORT);
        }
    }
    else {
//        Serial.println("  no wifi");
    }

    return 1;
}