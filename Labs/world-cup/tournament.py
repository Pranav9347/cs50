# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():
    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = [] # A list of dictionaries, each dictionary containing 2 pairs: {"team": "<team_name>", "rating": <rating>}
    # TODO: Read teams into memory from file
    with open(f"{sys.argv[1]}") as file:
        file_reader = csv.DictReader(file)
        for row in file_reader:
            d = {"team": row["team"], "rating": int(row["rating"])}
            teams.append(d)

    counts = {} # A dictionary of pairs, each pair <team_name>:count(no. of times it has won in N simulations)
    # TODO: Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner_name = simulate_tournament(teams)
        if winner_name in counts:
            counts[winner_name] = counts[winner_name] + 1
        else:
            counts[winner_name] = 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    winners = teams.copy()
    while not len(winners) == 1:
        w = simulate_round(winners)
        winners = w.copy()
    # here winners contains the winner of the tournament
    return (winners[0])["team"]


if __name__ == "__main__":
    main()
