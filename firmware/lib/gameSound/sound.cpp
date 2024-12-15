#include <sound.h>


const int melody[] = {
  NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, 
  NOTE_G4, NOTE_E4, NOTE_C4, NOTE_G4, 
  NOTE_C4, NOTE_F4, NOTE_A4, NOTE_C5,
  NOTE_A4, NOTE_F4, NOTE_C4, NOTE_A4
};

// Note durations: 4 = quarter note, 8 = eighth note, etc.
const int noteDurations[] = {
  8, 8, 4, 4, 
  8, 8, 4, 4, 
  8, 8, 4, 4,
  8, 8, 4, 4
};

const int gameOverMelody[] = {
  NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};

const int gameOverNoteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 4
};

unsigned long previousNoteTime = 0;
int currentNote = 0;
bool isTonePlaying = false;

void backgroundMusic(uint8_t SPKR_PIN)
{
  unsigned long currentTime = millis();
  
  // Check if it's time to play the next note
  if (!isTonePlaying || (currentTime - previousNoteTime >= (unsigned long)(1000 / noteDurations[currentNote]))) {
    if (isTonePlaying) {
      noTone(SPKR_PIN); // Stop the current tone
      isTonePlaying = false;
    } else {
      // Play the next note
      int duration = 1000 / noteDurations[currentNote];
      tone(SPKR_PIN, melody[currentNote], duration);
      previousNoteTime = currentTime;
      isTonePlaying = true;

      // Move to the next note
      currentNote++;
      if (currentNote >= (int) (sizeof(melody) / sizeof(melody[0]))) {
        currentNote = 0; // Restart the melody
      }
    }
  }
}

void playGameOverTune(uint8_t SPKR_PIN) {
  for (int i = 0; i < sizeof(gameOverMelody) / sizeof(gameOverMelody[0]); i++) {
    int duration = 1000 / noteDurations[i]; // Convert to milliseconds
    tone(SPKR_PIN, gameOverMelody[i], duration);
    delay(duration * 1.3);  // Add a short delay between notes
    noTone(SPKR_PIN);       // Stop the tone before playing the next note
  }
}