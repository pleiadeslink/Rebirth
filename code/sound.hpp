#ifndef c_sound_hpp
#define c_sound_hpp

class c_sound
{
	private:
		sf::Music ambience;

	public:
		c_sound() {}
        void playAmbience(std::string track);
};

#endif