void c_sound::update() {
    if(ambienceVol < 100.f) {
        ambienceVol = ambienceVol + 0.1f;
    }
    ambience.setVolume(ambienceVol);
}

void c_sound::playAmbience(std::string track) {
    if(ambience.openFromFile("data/sound/ambience/" + track + ".wav")) {
        ambienceVol = 0;
        sf::Time duration = ambience.getDuration();
        int randomTime = c_helper::random(1, duration.asMilliseconds());
        sf::Time start = sf::milliseconds(randomTime);
        ambience.play();
        ambience.setPlayingOffset(start);
        ambience.setLoop(true);
    }
}