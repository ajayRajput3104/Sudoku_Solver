function sayHello() {
  alert("You clicked the button! 🚀");
}

const grid = document.querySelector(".sudoku-grid");

for (let i = 0; i < 81; i++) {
  const cell = document.createElement("input");
  cell.className = "cell";
  cell.type = "text";
  cell.maxLength = 1; // Limit to 1 character
  cell.inputMode = "numeric"; // Show number keypad on mobile

  cell.addEventListener("input", (e) => {
    const val = e.target.value;
    if (!/^[1-9]$/.test(val)) {
      alert(`Only numeric Values are Allowed`) 
      e.target.value = ""; // Clear invalid input
    }
  });

  grid.appendChild(cell);
}


const cells = document.querySelectorAll(".cell");

document.getElementById("solveBtn").addEventListener("click", async () => {
  const status = document.getElementById("statusMessage");
  status.textContent = "Solving...";
  status.style.color = "orange";

  // Extract board
  let board = [];
  for (let i = 0; i < 9; i++) {
    let row = [];
    for (let j = 0; j < 9; j++) {
      const val = cells[i * 9 + j].value.trim();
      row.push(val === "" ? "." : val);
    }
    board.push(row);
  }

  try {
    const res = await fetch("http://localhost:18080/solve", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(board)
    });

    if (!res.ok) throw new Error("Invalid puzzle or server error");

    const solved = await res.json();

    // Update grid with solution
    for (let i = 0; i < 9; i++) {
      for (let j = 0; j < 9; j++) {
        cells[i * 9 + j].value = solved[i][j];
      }
    }

    status.textContent = "Solved successfully!";
    status.style.color = "lightgreen";
  } catch (err) {
    status.textContent = "Failed to solve puzzle.";
    status.style.color = "red";
    console.error(err);
  }
});

document.addEventListener("keydown", (e) => {
  const active = document.activeElement;
  if (!active.classList.contains("cell")) return;

  const index = Array.from(cells).indexOf(active);
  let row = Math.floor(index / 9);
  let col = index % 9;

  switch (e.key) {
    case "ArrowUp":
      row = (row - 1 + 9) % 9;
      break;
    case "ArrowDown":
      row = (row + 1) % 9;
      break;
    case "ArrowLeft":
      col--;
      if (col < 0) {
        col = 8;
        row = (row - 1 + 9) % 9;
      }
      break;
    case "ArrowRight":
      col++;
      if (col > 8) {
        col = 0;
        row = (row + 1) % 9;
      }
      break;
    default:
      return; // Ignore other keys
  }

  e.preventDefault();
  const newIndex = row * 9 + col;
  cells[newIndex].focus();
});

