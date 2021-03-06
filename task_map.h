#ifndef _TASK_MAP_H
#define _TASK_MAP_H

#include "util.h"
#include "entity_set.h"

class Task;
class Creature;

template<typename CostInfo>
class TaskMap {
  public:
  TaskMap(Rectangle bounds);
  Task* addTask(PTask, const Creature*);
  Task* addPriorityTask(PTask, const Creature*);
  Task* addTask(PTask, Vec2);
  Task* getTask(const Creature*);
  bool hasTask(const Creature*) const;
  const vector<Task*>& getTasks(Vec2) const;
  vector<const Task*> getAllTasks() const;
  const Creature* getOwner(const Task*) const;
  optional<Vec2> getPosition(Task*) const;
  void takeTask(const Creature*, Task*);
  void freeTask(Task*);
  void freeFromTask(Creature*);

  Task* addTaskCost(PTask, Vec2 pos, CostInfo);
  void markSquare(Vec2 pos, HighlightType, PTask);
  void unmarkSquare(Vec2 pos);
  Task* getMarked(Vec2 pos) const;
  HighlightType getHighlightType(Vec2 pos) const;
  CostInfo removeTask(Task*);
  CostInfo removeTask(UniqueEntity<Task>::Id);
  bool isPriorityTask(const Task*) const;
  bool hasPriorityTasks(Vec2) const;
  void freeTaskDelay(Task*, double delayTime);
  void setPriorityTasks(Vec2 pos);
  Task* getTaskForWorker(Creature* c);
  const map<Task*, CostInfo>& getCompletionCosts() const;

  SERIALIZATION_DECL(TaskMap);

  private:
  BiMap<const Creature*, Task*> SERIAL(creatureMap);
  unordered_map<Task*, Vec2> SERIAL(positionMap);
  Table<vector<Task*>> SERIAL(reversePositions);
  vector<PTask> SERIAL(tasks);
  Table<Task*> SERIAL(marked);
  Table<HighlightType> SERIAL(highlight);
  map<Task*, CostInfo> SERIAL(completionCost);
  map<UniqueEntity<Creature>::Id, double> SERIAL(delayedTasks);
  EntitySet<Task> SERIAL(priorityTasks);
};
namespace boost { 
namespace serialization {
template<typename CostInfo>
struct version<TaskMap<CostInfo>>
{
    BOOST_STATIC_CONSTANT(unsigned int, value = 1);
};
}
}

#endif
