const moves         = document.getElementById("moves");
const timeValue     = document.getElementById("time");
// const startButton   = document.getElementById("start");
const easyButton    = document.getElementById("easy");
const mediumButton  = document.getElementById("medium");
const hardButton    = document.getElementById("hard");
const stopButton    = document.getElementById("stop");
const gameContainer = document.querySelector(".game-container");
const result        = document.getElementById("result");
const controls      = document.querySelector(".controls-container");

let interval;
let cards,firstCard = false,secondCard= false,firstCardClicked = false;
let seconds=0,minutes=0,totalSeconds=0;
let movesCount=0,winCount=0;

const items =  [
                { name: "Edgar",    image: "images/Edgar.webp" },
                { name: "El-Primo", image: "images/El-Primo.webp"  },
                { name: "Griff",    image: "images/Griff.webp" },
                { name: "Jacky",    image: "images/Jacky.webp" },
                { name: "Janet",    image: "images/Janet.webp" },
                { name: "Jessie",   image: "images/Jessie.webp"},
                { name: "Lou",      image: "images/Lou.webp"   },
                { name: "Mandy",    image: "images/Mandy.webp" },
                { name: "Mortis",   image: "images/Mortis.webp"},
                { name: "Piper",    image: "images/Piper.webp" },
                { name: "Shelly",   image: "images/Shelly.webp"},
                { name: "Spike",    image: "images/Spike.webp" },
];

easyButton.addEventListener('click', () => {
  totalSeconds = 60; // Set totalSeconds to 60 for easy difficulty
  start()
});

mediumButton.addEventListener('click', () => {
  totalSeconds = 45; // Set totalSeconds to 45 for medium difficulty
  start();
});

hardButton.addEventListener('click', () => {
  totalSeconds = 30; // Set totalSeconds to 30 for hard difficulty
  start();
});

const timeGenerator = () => {
    // seconds += 1;
    // //minutes logic
    // if (seconds >= 60) {
    //   minutes += 1;
    //   seconds = 0;
    // }
    // //format time before displaying
    minutes = Math.floor(totalSeconds / 60);
    seconds = totalSeconds % 60;
    // Update the timer display
    let secondsValue = seconds < 10 ? `0${seconds}` : seconds;
    let minutesValue = minutes < 10 ? `0${minutes}` : minutes;
    timeValue.innerHTML = `<span>Time:</span>${minutesValue}:${secondsValue}`;
    // Decrement the seconds
    totalSeconds--;

    // If the remaining time reaches 0, stop the timer and end the game
    if (totalSeconds < 0) {
      clearInterval(interval);
      result.innerHTML = `<h2>You Looooose</h2>
      <h4>Matches: ${winCount} | Moves: ${movesCount}</h4>`;
      stopGame(); // Call a function to end the game with a "loss"
    }
   // Update the timer every second (1000 milliseconds) 
};

const movesCounter = () => {
    movesCount += 1;
    moves.innerHTML = `<span>Moves:</span>${movesCount}`;
};

const generateRandom = (size = 4) => {
    let tempArray = [...items];
    let cardValues = [];
    size = (size * size) / 2;
    for (let i = 0; i < size; i++) {
      const randomIndex = Math.floor(Math.random() * tempArray.length);
      cardValues.push(tempArray[randomIndex]);
      tempArray.splice(randomIndex, 1);
    }
    return cardValues;
};

function removeMatchingCards(card1, card2) {
  // Wait for the transition to finish before actually removing the cards
  setTimeout(function() {
    card1.classList.add('fade-out');
    card2.classList.add('fade-out');
    card1.style.opacity = '0';
    card2.style.opacity = '0';
  }, 700); // Wait for 0.5 seconds (the same duration as the transition)
};


const matrixGenerator = (cardValues, size = 4) => {
    gameContainer.innerHTML = "";
    cardValues = [...cardValues, ...cardValues];
    //simple shuffle
    cardValues.sort(() => Math.random() - 0.5);
    for (let i = 0; i < size * size; i++) {
      /*
          Create Cards
          before => front side (contains question mark)
          after => back side (contains actual image);
          data-card-values is a custom attribute which stores the names of the cards to match later
        */
      gameContainer.innerHTML += `
       <div class="card-container" data-card-value="${cardValues[i].name}">
          <div class="card-before">
            ?
          </div>
          <div class="card-after">
            <img src="${cardValues[i].image}" class="image"/>
          </div>
       </div>
       `;
    }
    //Grid
    gameContainer.style.gridTemplateColumns = `repeat(${size},auto)`;
    //Cards
    cards = document.querySelectorAll(".card-container");
    cards.forEach((card) => {
      card.addEventListener("click", () => {
        if (!firstCardClicked)
          startTimer();
        //If selected card is not matched yet then only run (i.e already matched card when clicked would be ignored)
        if (!card.classList.contains("matched")) {
          //flip the cliked card
          card.classList.add("flipped");
          //if it is the firstcard (!firstCard since firstCard is initially false)
          if (!firstCard) {
            //so current card will become firstCard
            firstCard = card;
            //current cards value becomes firstCardValue
            firstCardValue = card.getAttribute("data-card-value");
          } else {
            if (firstCard === card) {
              return;
            }
            //increment moves since user selected second card
            movesCounter();
            //secondCard and value
            secondCard = card;
            let secondCardValue = card.getAttribute("data-card-value");
            if (firstCardValue == secondCardValue) {
              //if both cards match add matched class so these cards would beignored next time
              firstCard.classList.add("matched");
              secondCard.classList.add("matched");
              // setTimeout(function() {
                removeMatchingCards(firstCard, secondCard);
              // }, 900);
              //set firstCard to false since next card would be first now
              firstCard = false;
              //winCount increment as user found a correct match
              winCount += 1;
              //check if winCount ==half of cardValues
              if (winCount == Math.floor(cardValues.length / 2)) {
                result.innerHTML = `<h2>You Won!</h2>
              <h4>Time Left: ${totalSeconds}s | Moves: ${movesCount}</h4>`;
                stopGame();
              }
            } else {
              
              //if the cards dont match
              //flip the cards back to normal
              let [tempFirst, tempSecond] = [firstCard, secondCard];
              firstCard = false;
              secondCard = false;
              
              
              setTimeout(() => {
                tempFirst.classList.add("shake");
                tempSecond.classList.add("shake");
              }, 700);
              tempFirst.classList.remove("shake");
                tempSecond.classList.remove("shake");
              let delay = setTimeout(() => {
                tempFirst.classList.remove("flipped");
                tempSecond.classList.remove("flipped");
              }, 900);
            }
          }
        }
      });
    });
  };
  //Start game
  // startButton.addEventListener("click", () => {
  //   movesCount = 0;
  //   totalSeconds = 10;
  //   minutes = Math.floor(totalSeconds / 60);
  //   seconds = totalSeconds % 60;
  //   // Update the timer display
  //   let secondsValue = seconds < 10 ? `0${seconds}` : seconds;
  //   let minutesValue = minutes < 10 ? `0${minutes}` : minutes;
  //   //controls amd buttons visibility
  //   controls.classList.add("hide");
  //   stopButton.classList.remove("hide");
  //   startButton.classList.add("hide");
  //   //initial moves
  //   moves.innerHTML = `<span>Moves:</span> ${movesCount}`;
  //   timeValue.innerHTML = `<span>Time:</span>${minutesValue}:${secondsValue}`;
  //   initializer();
  // });

  function start(){

    movesCount = 0;
    minutes = Math.floor(totalSeconds / 60);
    seconds = totalSeconds % 60;
    // Update the timer display
    let secondsValue = seconds < 10 ? `0${seconds}` : seconds;
    let minutesValue = minutes < 10 ? `0${minutes}` : minutes;
    //controls amd buttons visibility
    controls.classList.add("hide");
    stopButton.classList.remove("hide");
    easyButton.classList.add("hide");
    mediumButton.classList.add("hide");
    hardButton.classList.add("hide");
    // startButton.classList.add("hide");
    //initial moves
    moves.innerHTML = `<span>Moves:</span> ${movesCount}`;
    timeValue.innerHTML = `<span>Time:</span>${minutesValue}:${secondsValue}`;
    initializer();
  };

  //Stop game
  stopButton.addEventListener("click", () => {
    stopGame(); // Call stopGame function when stop button is clicked
  });
  
  function startTimer() {
    firstCardClicked = true;
    interval = setInterval(timeGenerator, 1000);
  }

  const stopGame = () => {
    controls.classList.remove("hide");
    stopButton.classList.add("hide");
    easyButton.classList.remove("hide");
    mediumButton.classList.remove("hide");
    hardButton.classList.remove("hide");
    // startButton.classList.remove("hide");
    clearInterval(interval); // clear the interval assigned to timer variable
  };
  //Initialize values and func calls
  const initializer = () => {
    result.innerText = "";
    winCount = 0;
    firstCardClicked = false;
    firstCard = false;
    secondCard= false;
    let cardValues = generateRandom();
    console.log(cardValues);
    matrixGenerator(cardValues);
  };