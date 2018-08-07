void c_gamelog::update() {
    if(newMessage == true) {
        v_gamelog.push_back(currentMessage);
    }
}

void c_gamelog::message(std::string str) {
    newMessage = true;
    currentMessage = currentMessage + " " + str;
    //engine -> message(str);
}

std::string c_gamelog::getLastMessage(const int& position) {
    int size = v_gamelog.size();
    std::string emptyMessage = "";
    if(size == 0 or position > size - 1) {
        return emptyMessage;
    }
    return v_gamelog[size - 1 - position];
}

void c_gamelog::clear() {
	currentMessage = "";
    newMessage = false;
}