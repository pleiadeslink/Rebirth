c_trigger::c_trigger(c_actor* father)
: father(father) {
}

void c_trigger::set(std::string command, const bool& autodelete) {
    this -> command = command;
    this -> autodelete = autodelete;
}