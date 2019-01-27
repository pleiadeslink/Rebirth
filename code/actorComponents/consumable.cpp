/*c_consumable::c_consumable(c_actor* father, const int& action, s_effect effect0, s_effect effect1, s_effect effect2, s_effect effect3)
: father(father) {
	this -> action = action;
	effect[0].script = effect0.script;
	effect[0].value1 = effect0.value1;
	effect[0].string1 = effect0.string1;
	effect[1].script = effect1.script;
	effect[1].value1 = effect1.value1;
	effect[1].string1 = effect1.string1;
	effect[2].script = effect2.script;
	effect[2].value1 = effect2.value1;
	effect[2].string1 = effect2.string1;
	effect[3].script = effect3.script;
	effect[3].value1 = effect3.value1;
	effect[3].string1 = effect3.string1;
}*/

c_consumable::c_consumable(c_actor* father, s_effect effect0, s_effect effect1, s_effect effect2, s_effect effect3)
: father(father) {
	effect[0].script = effect0.script;
	effect[0].value1 = effect0.value1;
	effect[0].string1 = effect0.string1;
	effect[1].script = effect1.script;
	effect[1].value1 = effect1.value1;
	effect[1].string1 = effect1.string1;
	effect[2].script = effect2.script;
	effect[2].value1 = effect2.value1;
	effect[2].string1 = effect2.string1;
	effect[3].script = effect3.script;
	effect[3].value1 = effect3.value1;
	effect[3].string1 = effect3.string1;
}

void c_consumable::consume(const int& consumer) {
	for(int i = 0; i < 4; ++i) {
		if(effect[i].script != "") {
			structEventData eventData;
    		eventData.emitter = consumer;
    		eventData.type = effect[i].script;
    		eventData.value1 = effect[i].value1;
    		eventData.string1 = effect[i].string1;
			engine -> game -> runEffect(eventData);
			std::cout << effect[i].string1 << std::endl;
		}
	}
}