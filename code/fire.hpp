#ifndef FIRE_EF_H
#define FIRE_EF_H

/// @brief Reimplementation of Doom's end level fire effect; to be used somehwere
class c_fire {

    protected:

        float          m_pixelSize;
        unsigned int   m_width;
        unsigned int   m_height;
        unsigned int** m_values;
        sf::Vector2f   m_origin;
        sf::RectangleShape currentPixel;
        // increases performance

    public:

        c_fire(float, unsigned int, unsigned int, sf::Vector2f);
        virtual ~c_fire();
        const static sf::Color colorPalette[37];
        void update();
        void render(sf::RenderWindow&);
        void setFireSourceStrength(int);
        unsigned int getFireSourceStrength() const;
        float getPixelSize() const { return m_pixelSize; };
        unsigned int getWidth() const { return m_width;  };
        unsigned int getHeight() const { return m_height; };
        unsigned int** getValues() const { return m_values; };
        sf::Vector2f getOrigin() const { return m_origin; };
};
#endif