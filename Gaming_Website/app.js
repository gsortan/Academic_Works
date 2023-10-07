/**
 * WEB222 – Final Assessment
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
 *      Date:       2023/08/09
 */

const { reviews } = window;

const input = document.querySelector("#post");

function resetReviewCards() {
  let mainPage = document.querySelector("#reviewPage");
  mainPage.innerHTML = "";
}

function displayReviews(reviews) {
  let mainPage = document.querySelector("#reviewPage");
  let review;
  for (review of reviews) {
    let cardHeader = document.createElement("div");
    let card = document.createElement("div");
    let ratingsBar = document.createElement("div");

    let name = document.createElement("h6");
    let dateElement = document.createElement("p");
    let reviewBlock = document.createElement("p");

    name.textContent = review.name;
    dateElement.textContent = review.date;
    reviewBlock.textContent = review.reviewText;

    for (let i = 0; i < review.rating; i++) {
      let image = document.createElement("img");
      image.src = "starRating.png";
      ratingsBar.appendChild(image);
      image.className = "image";
    }

    ratingsBar.className = "RateBar";
    reviewBlock.className = "rateReviewContainer";
    card.className = "card";
    cardHeader.className = "cardHeader";

    cardHeader.appendChild(name);
    cardHeader.appendChild(dateElement);
    card.appendChild(cardHeader);
    card.appendChild(ratingsBar);
    card.appendChild(reviewBlock);
    mainPage.appendChild(card);
  }
}

function addReview() {
  let form = document.querySelector("#post");
  form.addEventListener("submit", (event) => {
    event.preventDefault();
    let name = document.querySelector("#name").value;
    let rating = document.querySelector("#rating").value;
    let reviewText = document.querySelector("#postReview").value;

    let date = new Date().toLocaleDateString();
    let newReview = {
      name,
      date,
      rating,
      reviewText
    };

    reviews.push(newReview);
    resetReviewCards();
    form.reset();
    displayReviews(reviews);
  });
}

function onLoad() {
  displayReviews(reviews);
  addReview();
}

window.addEventListener("load", onLoad);
