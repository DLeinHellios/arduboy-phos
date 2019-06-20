#ifndef SOUNDS_H
#define SOUNDS_H


// -- Sound Object --
ArduboyTones sound(arduboy.audio.enabled);



// -- Tones Arrays --
const uint16_t PROGMEM eliteTones[] =
{
    NOTE_G3,125, NOTE_C4,125, NOTE_G4,125, NOTE_C5,100,
    TONES_END
};


const uint16_t PROGMEM lastLifeTones[] =
{
    NOTE_G5,75, NOTE_REST,50, NOTE_G5,75, NOTE_REST,50,
    NOTE_G5,75, NOTE_REST,50, TONES_END
};


const uint16_t PROGMEM deathTones[] =
{
    NOTE_G2,150, NOTE_FS2,150, NOTE_C2,600, TONES_END
};



// -- Sound Functions --
void shootSound() {
    // Single shoot tone
    if(!sound.playing()) {
        sound.tone(NOTE_C3,100);
    }
}


void enemyKillSound(bool phosActive) {
    // Single kill tone
    if(phosActive) {
        sound.tone(NOTE_C4,125);
    }
}


void eliteHitSound(bool phosActive) {
    // Single hit tone
    if(phosActive) {
        sound.tone(NOTE_G3,125);
    }
}


void eliteKillSound(bool phosActive) {
    // Several tones ascending
    if(phosActive) {
        sound.tones(eliteTones);
    }
}


void deathSound() {
    // Several tones descending
    sound.tones(deathTones);
}


void lastLifeSound() {
    // Three single tones
    sound.tones(lastLifeTones);
}


#endif
