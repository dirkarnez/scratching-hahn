#include <iostream>
#include "SoundTouch/SoundTouch.h"
#include "sndfile.hh"

using namespace soundtouch;

int main(int argc, char** argv) {
    // Load the audio file to be scratched
    SndfileHandle input_file("../audio/440Hz.wav");
    int num_channels = input_file.channels();
    int sample_rate = input_file.samplerate();
    int num_frames = input_file.frames();
    float* audio_data = new float[num_channels * num_frames];
    input_file.read(audio_data, num_channels * num_frames);

    // Set the scratch duration in seconds and the scratch speed in semitones per second
    float scratch_duration = 5;
    float scratch_speed = -2.0;

    // Calculate the scratch length in samples
    int scratch_length = static_cast<int>(scratch_duration * sample_rate);

    // Create a SoundTouch object with the desired scratch speed
    SoundTouch soundtouch;
    soundtouch.setPitchSemiTones(scratch_speed);
    soundtouch.setSampleRate(sample_rate);
    soundtouch.setChannels(num_channels);
    
    // Apply the turntable scratch effect to the audio
    for (int i = 0; i < scratch_length; i++) {
        float scratch_ratio = static_cast<float>(i) / scratch_length;
        int scratch_position = num_channels * (num_frames - scratch_length + i);
        for (int j = 0; j < num_channels; j++) {
            audio_data[scratch_position + j] *= scratch_ratio;
        }
        
        soundtouch.putSamples(&audio_data[scratch_position], num_channels);
    }

    // Save the scratched audio to a new file
    SndfileHandle output_file("scratched_audio.wav", SFM_WRITE, input_file.format(), num_channels, sample_rate);
    output_file.write(audio_data, num_channels * num_frames);

    // Clean up
    delete[] audio_data;

    return 0;
}