const GAME_TIME = 90;

let timeLeft, score, combo, hearts;
let level = 1;
let reactions = [];
let lastTap = 0;
let gameActive = false;

let currentRule = {};
let isCorrectTarget = false;

function showScreen(id) {
  document.querySelectorAll(".screen").forEach(s => s.classList.remove("active"));
  document.getElementById(id).classList.add("active");
}

function startGame() {
  timeLeft = GAME_TIME;
  score = 0;
  combo = 0;
  hearts = 5;
  reactions = [];
  gameActive = true;

  updateHUD();
  showScreen("game");
  nextStimulus();

  timer = setInterval(() => {
    timeLeft--;
    updateLevel();
    updateHUD();
    if (timeLeft <= 0) endGame(true);
  }, 1000);
}

function updateLevel() {
  if (timeLeft <= 60 && timeLeft > 30) level = 2;
  if (timeLeft <= 30) level = 3;
}

function updateHUD() {
  document.getElementById("time").innerText = timeLeft + "s";
  document.getElementById("score").innerText = score;
  document.getElementById("combo").innerText = combo;
  document.getElementById("hearts").innerText = "❤️".repeat(hearts);
}

function nextStimulus() {
  if (!gameActive) return;

  const stim = document.getElementById("stimulus");
  const rule = document.getElementById("rule");

  // Random shape
  const shapes = ["●", "■", "▲"];
  const colors = ["blue", "red", "green", "yellow", "purple"];
  const shape = shapes[Math.floor(Math.random()*shapes.length)];
  const color = colors[Math.floor(Math.random()*colors.length)];

  stim.innerText = shape;
  stim.style.color = color;
  stim.style.transform = "scale(1.1)";
  setTimeout(() => stim.style.transform = "scale(1)", 120);

  // RULES BASED ON LEVEL
  if (level === 1) {
    rule.innerHTML = "Tap when <b>BLUE ●</b>";
    isCorrectTarget = (color === "blue" && shape === "●");
  }

  if (level === 2) {
    rule.innerHTML = "Tap when <b>GREEN ■</b>, avoid RED";
    isCorrectTarget = (color === "green" && shape === "■");
  }

  if (level === 3) {
    rule.innerHTML = "Tap when <b>YELLOW ▲</b>, HOLD for PURPLE ●";
    isCorrectTarget = (color === "yellow" && shape === "▲");
  }

  setTimeout(nextStimulus, Math.max(350, 900 - combo * 40));
}

function registerTap() {
  if (!gameActive) return;

  const now = performance.now();
  if (lastTap) reactions.push(now - lastTap);
  lastTap = now;

  if (isCorrectTarget) {
    score++;
    combo++;
  } else {
    hearts--;
    combo = 0;
    if (hearts <= 0) endGame(false);
  }

  updateHUD();
}

function endGame(success) {
  gameActive = false;
  clearInterval(timer);

  if (success) showProfile();
  else showScreen("gameover");
}

function showProfile() {
  const avg = reactions.reduce((a,b)=>a+b,0)/reactions.length || 500;

  document.getElementById("reflex").innerText = Math.min(100, (1000/avg)*100).toFixed(0);
  document.getElementById("focus").innerText = Math.max(0, 100 - (5-hearts)*15);
  document.getElementById("adapt").innerText = Math.min(100, level * 30);
  document.getElementById("stability").innerText = Math.min(100, combo * 10);

  showScreen("profile");
}

function restart() {
  showScreen("menu");
}
