# Project Proposal
**Overview**
A simple 2D action game similar to games like flappy bird or super mario in which the player's character has to jump over/maneuver around obstacles. All of the character's movements will be controlled by the player's voice, like in the game "Eighth Note! Don't stop". Sounds that the mic picks up will cause the character to move forward (soft sounds for just walking, loud sounds for jumping over obstacles - the louder the sound, the higher the character will jump)

**Libraries I plan to use:**
* Essentia: Open-source library and tools for audio and music analysis, description and synthesis (http://essentia.upf.edu/documentation/index.html)
* ofxAudioAnalyzer: openFrameworks addon for audio analysis (https://github.com/leozimmerman/ofxAudioAnalyzer)
* ofxGUI
* openFrameworks Graphics module
* openFrameworks Sound module

**Timeline:**
* By April 20:
  - [] start basic working GUI for the game (without the voice controlled component - have it working with keyboard controls for now until I can get the voice controlled aspect to work with the game)
  - [] figure out how the sound analysis libraries (Essentia, ofxAudioAnalyzer) work and plan out how I'll use them for the voice controlled aspect of this game
  - [] write some simple funtions/tests for some of the sound stuff
  - [] write necessary tests for completed portions
  
* By April 27:
  - [] integrate the voice controlled aspect of the game
  - [] make improvements to graphics
  - [] have a way to keep track of different player's scores
  - [] write necessary tests for completed portions
  
* By May 2:
  - [] add different levels/modes for the game
  - [] write necessary tests for completed portions
  - [] clean up
