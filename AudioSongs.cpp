#include "AudioSongs.h"

#include <iostream>

AudioSongs::AudioSongs(const vector<string>& filepaths)
    : currentSongIndex(0)
{
    for (const auto& filepath : filepaths)
    {
        shared_ptr<SoundBuffer> buffer = make_shared<SoundBuffer>();

        if (!buffer->loadFromFile(filepath))
        {
            cout << "Error loading audio file: " << filepath << endl;
        }

        buffers.push_back(buffer);

        Sound sound;
        sound.setVolume(20);
        sound.setBuffer(*buffers.back());
        sounds.push_back(sound);
    }
}

void AudioSongs::Update()
{
    if (sounds[currentSongIndex].getStatus() == Sound::Stopped)
    {
        // The current song has finished playing, start the next one
        currentSongIndex = (currentSongIndex + 1) % sounds.size();
        sounds[currentSongIndex].play();
    }
}
