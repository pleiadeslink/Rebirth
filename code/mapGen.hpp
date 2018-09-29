#ifndef c_mapGen_hpp
#define c_mapGen_hpp

class c_mapGen : public c_map {
    private:
        c_tile** matrix;
        int width;
        int height;

    public:
        c_mapGen() { }
        ~c_mapGen() { }
        static const bool& generate(std::string type); // Static call, launch the generator
        void copyToSource() {} // Copy map to c_map
};

#endif