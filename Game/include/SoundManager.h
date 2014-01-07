#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#pragma once
#include "Globals.h"

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();

        void playPowerUp1Sound(void);
        void playPowerUp2Sound(void);
        void playPowerUp3Sound(void);
        void playPowerUp4Sound(void);
        void playPowerUp5Sound(void);
        void playCrashSound(void);
        void playExplotionSound(void);
        void playMenuSound(void);

    protected:
    private:
        FSOUND_SAMPLE* powerup1;
        FSOUND_SAMPLE* powerup2;
        FSOUND_SAMPLE* powerup3;
        FSOUND_SAMPLE* powerup4;
        FSOUND_SAMPLE* powerup5;
        FSOUND_SAMPLE* crash;
        FSOUND_SAMPLE* explotion;
        FSOUND_SAMPLE* menu_select;
};

#endif // SOUNDMANAGER_H
