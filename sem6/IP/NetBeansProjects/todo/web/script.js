tasks = [];

function fetchTasksFromDatabase() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
//      console.log("this:" + JSON.parse(xhttp.reponseText));
      tasks = JSON.parse(xhttp.responseText);
      renderTasks();
    }
  };
  xhttp.open("GET", "/todo/task", true);
  xhttp.send();
}

//function saveTasksToLocalStorage() {
//  localStorage.setItem("tasks", JSON.stringify(tasks));
//}

//function loadTasksFromLocalStorage() {
//  const storedTasks = localStorage.getItem("tasks");
//  tasks = storedTasks ? JSON.parse(storedTasks) : [];
//  renderTasks();
//}

window.onload = function () {
  //  loadTasksFromLocalStorage();
  fetchTasksFromDatabase();
};

function addTask() {
  const taskInput = document.getElementById("taskInput");
  const taskText = taskInput.value.trim();

  if (taskText !== "") {
    const task = {
      id: Date.now(),
      text: taskText,
    };
    tasks.push(task);
    renderTasks();
    taskInput.value = "";
    saveTasktoDatabase(task);
//    saveTasksToLocalStorage();
  }
}

function removeTask(taskId) {
  tasks = tasks.filter((task) => task.id !== taskId);
  renderTasks();
  deleteTaskFromDatabase(taskId);
//  saveTasksToLocalStorage();
}

function renderTasks() {
  const taskList = document
    .getElementById("taskList")
    .getElementsByTagName("tbody")[0];
  taskList.innerHTML = "";
  tasks.forEach((task) => {
    const row = document.createElement("tr");
    const taskCell = document.createElement("td");
    const actionCell = document.createElement("td");
    const minusButton = document.createElement("button");

    taskCell.textContent = task.text;
    minusButton.textContent = "-";
    minusButton.onclick = () => removeTask(task.id);

    actionCell.appendChild(minusButton);

    row.appendChild(taskCell);
    row.appendChild(actionCell);

    taskList.appendChild(row);
  });
}

function clearAll() {
  console.log("clearAll");
  tasks = [];
  renderTasks();
  clearDatabase();
}

function saveTasktoDatabase(task) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      console.log(this.responseXML);
    }
  };
  xhttp.open(
    "POST",
    `/todo/task?id=${encodeURIComponent(task.id)}&text=${encodeURIComponent(
      task.text
    )}`,
    true
  );
  xhttp.send();
  //  const taskParams = Object.entries(task).map(([key, value]) => `${encodeURIComponent(key)}=${encodeURIComponent(value)}`).join("&");
  //  console.log(taskParams);
  //  xhttp.send(taskParams);
  //    const taskParams = new URLSearchParams();
  //    taskParams.append("id", task.id);
  //    taskParams.append("text", task.text);
  //    console.log(taskParams.toString());
  //    xhttp.send(taskParams.toString());
}

function deleteTaskFromDatabase(taskId) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      console.log(this.responseXML);
    }
  };
  xhttp.open("DELETE", `/todo/task/${taskId}`, true);
  xhttp.send();
}

function clearDatabase() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
      console.log(this.responseXML);
    }
  };
  xhttp.open("DELETE", `/todo/task/`, true);
  xhttp.send();
}
