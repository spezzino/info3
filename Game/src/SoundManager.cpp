#include <stdio.h>
#include "SoundManager.h"

int channel_menu_music=-1;
int channel_game_music=-1;

SoundManager::SoundManager()
{
    FSOUND_Init (44100, 16, 0); //sample ratio, channels
    powerup1 = FSOUND_Sample_Load(FSOUND_FREE,"audio/powerup1.wav",0,0,0); //channel, file
    powerup2 = FSOUND_Sample_Load(FSOUND_FREE,"audio/powerup2.wav",0,0,0);
    powerup3 = FSOUND_Sample_Load(FSOUND_FREE,"audio/powerup3.wav",0,0,0);
    powerup4 = FSOUND_Sample_Load(FSOUND_FREE,"audio/powerup4.wav",0,0,0);
    powerup5 = FSOUND_Sample_Load(FSOUND_FREE,"audio/powerup5.wav",0,0,0);
    crash = FSOUND_Sample_Load(FSOUND_FREE,"audio/crash.wav",0,0,0);
    explotion = FSOUND_Sample_Load(FSOUND_FREE,"audio/explosion.wav",0,0,0);
    menu_select = FSOUND_Sample_Load(FSOUND_FREE,"audio/menu_select.wav",0,0,0);
    menu_music = FSOUND_Sample_Load(FSOUND_FREE,"audio/menu_music.mp3",0,0,0);
    game_music = FSOUND_Sample_Load(FSOUND_FREE,"audio/game_music.mp3",0,0,0);
}

SoundManager::~SoundManager()
{
    FSOUND_Sample_Free (powerup1);
    FSOUND_Sample_Free (powerup2);
    FSOUND_Sample_Free (powerup3);
    FSOUND_Sample_Free (powerup4);
    FSOUND_Sample_Free (powerup5);
    FSOUND_Sample_Free (crash);
    FSOUND_Sample_Free (explotion);
    FSOUND_Sample_Free (menu_select);
    FSOUND_Sample_Free (menu_music);
    FSOUND_Sample_Free (game_music);
    FSOUND_Close();
}

void SoundManager::playPowerUp1Sound()
{
    FSOUND_PlaySound (FSOUND_FREE,powerup1);
}

void SoundManager::playPowerUp2Sound()
{
    FSOUND_PlaySound (FSOUND_FREE,powerup2);
}

void SoundManager::playPowerUp3Sound()
{
    FSOUND_PlaySound (FSOUND_FREE,powerup3);
}

void SoundManager::playPowerUp4Sound()
{
    FSOUND_PlaySound (FSOUND_FREE,powerup4);
}

void SoundManager::playPowerUp5Sound()
{
    FSOUND_PlaySound (FSOUND_FREE,powerup5);
}

void SoundManager::playCrashSound()
{
    FSOUND_PlaySound (FSOUND_FREE,crash);
}

void SoundManager::playExplotionSound()
{
    FSOUND_PlaySound (FSOUND_FREE,explotion);
}

void SoundManager::playMenuSound()
{
    FSOUND_PlaySound (FSOUND_FREE,menu_select);
}

void SoundManager::playMenuMusic()
{
    if (channel_menu_music == -1)
    {
        // Caso en el que no tenga asignado ningun canal debe reproducir
        channel_menu_music = FSOUND_PlaySound (FSOUND_FREE,menu_music);
    }
}

void SoundManager::stopMenuMusic()
{
    if(channel_menu_music != -1 )
    {
        printf("Debo apagar musica menu");
        FSOUND_StopSound(channel_menu_music);
        channel_menu_music = -1;
    }
}

void SoundManager::playGameMusic()
{
    if (channel_game_music == -1)
    {
        channel_game_music = FSOUND_PlaySound (FSOUND_FREE,game_music);
    }
}

void SoundManager::stopGameMusic()
{
    if(channel_game_music != -1 )
    {
        printf("Debo apagar musica juego");
        FSOUND_StopSound(channel_game_music);
        channel_game_music = -1;
    }
}
