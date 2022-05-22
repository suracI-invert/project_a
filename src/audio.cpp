// #include"audio.h"

// audioFX::audioFX(const char* path) {
//     qSoundFX=Mix_LoadWAV(path);
//     if(qSoundFX) throw std::runtime_error{"Failed to load sound effect: " + std::string{path} + "\n" + "Error: " + Mix_GetError()};
// }

// audioFX::~audioFX() {
//     Mix_FreeChunk(qSoundFX);
// }

// void audioFX::play(int channel, int repeat) {
//     Mix_PlayChannel(channel, qSoundFX, repeat);
// }

// void audioFX::halt(int channel) {
//     Mix_HaltChannel();
// }

// music::music(const char* path) {
//     mus=Mix_LoadMUS(path);
//     if(!music) throw std::runtime_error{"Failed to load music: " + std::string{path} + "\n" + "Error: " + Mix_GetError()};
// }

// music::~music() {
//     Mix_FreeMusic(mus);
// }

// void music::play(int repeat) {
//     Mix_PlayMusic(mus, repeat);
// }

// void music::halt() {
//     Mix_HaltMusic();
// }

// void music::pause() {
//     Mix_PauseMusic();
// }

// void music::resume() {
//     Mix_ResumeMusic();
// }