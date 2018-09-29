// Static call, launches the generator
const bool& c_mapGen::generate(std::string type) {
    c_mapGen gen;
    gen.createMatrix();
    return true;
}