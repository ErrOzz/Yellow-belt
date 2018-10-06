#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const {
    return devs_tasks_.at(person);
  }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person) {
    ++devs_tasks_[person][TaskStatus::NEW];
  }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
	  auto& dev_tasks_ = devs_tasks_[person];
	  vector<TaskStatus> tasks_;
	  TasksInfo updated_tasks_;
	  TasksInfo untouched_tasks_;
  // Создаём вектор задач для удобства обработки
	  for (const auto& task_ : dev_tasks_) {
		  TaskStatus task_name_ = task_.first;
		  int task_qtty_ = task_.second;
		  vector<TaskStatus> to_add_(task_qtty_, task_name_);
		  tasks_.insert(tasks_.end(), to_add_.begin(), to_add_.end());
	  }

	  dev_tasks_.clear();
  // Обновляем задачи в векторе в соответствии с task_count
	  int i = 0;
	  for (auto& task_ : tasks_) {
		  if (task_ == TaskStatus::DONE || i == task_count) break;
		  task_ = static_cast<TaskStatus>(static_cast<int>(task_) + 1);
		  ++i;
	  }
  // Обновляем task_count в соответствии с фактическим количеством невыполненных задач
	  task_count = i;
  // Восстанавливаем словарь задач для разработчика и создаём словари обновленных и неизменённых задач
	  i = 0;
	  for (auto & task_ : tasks_) {
		  ++dev_tasks_[task_];
		  if (i < task_count) {
			  ++updated_tasks_[task_];
		  } else if (task_ != TaskStatus::DONE) {
			  ++untouched_tasks_[task_];
		  }
		  ++i;
	  }

	  return make_tuple(updated_tasks_, untouched_tasks_);
  }

private:
  map<string, TasksInfo> devs_tasks_;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	for (const auto& task : tasks_info) {
		switch (task.first) {
			case TaskStatus::NEW:
				cout << "NEW: ";
				break;
			case TaskStatus::IN_PROGRESS:
				cout << "PRG: ";
				break;
			case TaskStatus::TESTING:
				cout << "TST: ";
				break;
			case TaskStatus::DONE:
				cout << "DON: ";
				break;
		}
		cout << task.second << ". ";
	}
	cout << endl;
}

int main() {
  TeamTasks tasks;
  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "TSKS: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 5);
  cout << "UPDD: ";
  PrintTasksInfo(updated_tasks);
  cout << "UNTD: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 5);
  cout << "UPDD: ";
  PrintTasksInfo(updated_tasks);
  cout << "UNTD: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 3);
  cout << "UPDD: ";
  PrintTasksInfo(updated_tasks);
  cout << "UNTD: ";
  PrintTasksInfo(untouched_tasks);

  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "TSKS: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 10);
  cout << "UPDD: ";
  PrintTasksInfo(updated_tasks);
  cout << "UNTD: ";
  PrintTasksInfo(untouched_tasks);

  cout << "TSKS: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 4);
  cout << "UPDD: ";
  PrintTasksInfo(updated_tasks);
  cout << "UNTD: ";
  PrintTasksInfo(untouched_tasks);

  cout << "TSKS: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  return 0;
}
