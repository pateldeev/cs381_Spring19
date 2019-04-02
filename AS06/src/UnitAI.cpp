#include <Aspect.h>
#include <Entity381.h>  //Aspect includes Entity381.h

UnitAI::UnitAI(Entity381* ent) :
	Aspect(ent) {

}

UnitAI::~UnitAI() {
	for (Command *c : commands) {
		c->Stop();
		delete c;
	}
}

void UnitAI::Tick(float dt) {
	if (!commands.empty()) {
		commands.front()->Tick(dt);

		if (commands.front()->Done()) {
			delete commands.front();
			commands.pop_front();
			if (!commands.empty())
				commands.front()->Init();
		}
	}
}

void UnitAI::SetCommand(Command *c) {
	RemoveAllCommands();
	commands.push_front(c);
	c->Init();
}

void UnitAI::AddCommand(Command *c) {
	commands.push_back(c);
	if (commands.front() == c)
		c->Init();
}

void UnitAI::RemoveAllCommands(void) {
	for (Command *c : commands) {
		c->Stop();
		delete c;
	}
	commands.clear();
}

void UnitAI::DrawBoundingBox(bool draw_all) const {
	if (!commands.empty())
		commands.front()->DrawBoundingBox(draw_all);
}
