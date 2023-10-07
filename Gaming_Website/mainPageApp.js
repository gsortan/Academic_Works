/**
 * WEB222 – Assignment 04
 *
 * I declare that this assignment is my own work in accordance with
 * Seneca Academic Policy. No part of this assignment has been
 * copied manually or electronically from any other source
 * (including web sites) or distributed to other students.
 *
 * Please update the following with your information:
 *
 *      Name:       Gordon Tan
 *      Student ID: 147206221
 *      Date:       2023/07/24
 */

// All of our data is available on the global `window` object.
// Create local variables to work with it in this file.

const input = document.querySelector("#emailBox");

input.addEventListener("invalid", function (event) {
  if (event.target.validity.patternMismatch) {
    event.target.setCustomValidity("This is an incorrect format for an email! Enter a valid one.");
  }

});





input.addEventListener("change", function (event) {
  event.target.setCustomValidity("");
});

function successfulSignUp()
{
  const submitButton = document.querySelector("input[type='submit']");
 
  if(input.checkValidity())
  {

alert("You've signed up!");
  }

  
}

function onLoad() {
  console.log("loaded");
}

window.addEventListener("load", onLoad);
