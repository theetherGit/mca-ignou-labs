// Outer loop: Determines the number to be printed (1 through 10)
for (let i = 1; i <= 10; i++) {
  let row = ""; // Reset the row string for the current number

  // Inner loop: Controls the frequency of the print
  // It runs 'i' times for the number 'i'
  for (let j = 1; j <= i; j++) {
    row += i + " "; // Append the number and a space to the row
  }

  // Print the completed row to the console
  console.log(row.trim());
}
