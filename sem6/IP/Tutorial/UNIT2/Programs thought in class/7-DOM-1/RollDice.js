var dieImages = new Array(6); // array to store img elements

// get die img elements
function start()
{
   var button = document.getElementById( "rollButton" );
   button.addEventListener( "click", rollDice, false );
   var length = dieImages.length; // get array's length once before loop

   for ( var i = 0; i < length; ++i )
   {
      dieImages[ i ] = document.getElementById( "die" + (i + 1) );
   } // end for
} // end function start

// roll the dice
function rollDice()
{
   var face;  // face rolled
   var length = dieImages.length;

   for ( var i = 0; i < length; ++i )
   {
      face = Math.floor( 1 + Math.random() * 6 );
      setImage( i, face ); // display appropriate die image
   } // end for

} // end function rollDice


// set image source for a die
function setImage( dieNumber, face )
{
   dieImages[ dieNumber ].setAttribute( "src", "die" + face + ".png" );
   dieImages[ dieNumber ].setAttribute( "alt", 
      "die with " + face + " spot(s)" );
} // end function setImage
window.addEventListener( "load", start, false );
