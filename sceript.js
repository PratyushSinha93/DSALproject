document.getElementById("addPlayerForm").addEventListener("submit", function(e) {
    e.preventDefault();
    const playerName = document.getElementById("playerName").value;
    const playerScore = document.getElementById("playerScore").value;

    // In a real-world scenario, this would send data to a server
    console.log(`Player Added: ${playerName}, Score: ${playerScore}`);

    // Simulate success message
    alert("Player added successfully!");
    document.getElementById("addPlayerForm").reset();
});

document.getElementById("deletePlayerForm").addEventListener("submit", function(e) {
    e.preventDefault();
    const playerName = document.getElementById("deletePlayerName").value;

    // In a real-world scenario, this would send data to a server
    console.log(`Player Deleted: ${playerName}`);

    // Simulate success message
    alert("Player deleted successfully!");
    document.getElementById("deletePlayerForm").reset();
});

document.getElementById("searchPlayerForm").addEventListener("submit", function(e) {
    e.preventDefault();
    const playerName = document.getElementById("searchPlayerName").value;

    // In a real-world scenario, this would send a GET request to the server
    console.log(`Search Player: ${playerName}`);

    // Simulate a search result
    alert(`Player found: ${playerName} with score 100`); // Example search result
    document.getElementById("searchPlayerForm").reset();
});

document.getElementById("viewLeaderboardBtn").addEventListener("click", function() {
    // Simulate leaderboard display
    console.log("Viewing leaderboard...");
    
    // Example leaderboard data
    const leaderboard = [
        { name: "John", score: 300 },
        { name: "Alice", score: 250 },
        { name: "Bob", score: 200 }
    ];

    let leaderboardHtml = "<table><thead><tr><th>Player Name</th><th>Score</th></tr></thead><tbody>";
    leaderboard.forEach(player => {
        leaderboardHtml += `<tr><td>${player.name}</td><td>${player.score}</td></tr>`;
    });
    leaderboardHtml += "</tbody></table>";

    document.getElementById("leaderboardDisplay").innerHTML = leaderboardHtml;
});
