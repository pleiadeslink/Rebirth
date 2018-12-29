void c_sound::playAmbience(std::string track) {
    std::cout << "Playing ambience '" << track << "'." << std::endl;
    ambience.openFromFile("data/sound/ambience/" + track + ".wav");
    ambience.play();
    ambience.setLoop(true);
}