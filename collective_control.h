#ifndef _COLLECTIVE_CONTROL_H
#define _COLLECTIVE_CONTROL_H

#include "monster_ai.h"

class Creature;
class Collective;
class Tribe;

class CollectiveControl {
  public:
  CollectiveControl(Collective*);
  virtual MoveInfo getMove(Creature*) = 0;
  virtual PTask getNewTask(Creature*);
  virtual void tick(double time) = 0;
  virtual void onCreatureKilled(const Creature* victim, const Creature* killer);

  SERIALIZATION_DECL(CollectiveControl);

  virtual ~CollectiveControl();

  static PCollectiveControl idle(Collective*);

  template <class Archive>
  static void registerTypes(Archive& ar);

  const vector<Creature*>& getCreatures() const;
  vector<Creature*>& getCreatures();

  protected:
  Collective* getCollective();
  const Collective* getCollective() const;

  private:
  Collective* SERIAL2(collective, nullptr);
};


#endif