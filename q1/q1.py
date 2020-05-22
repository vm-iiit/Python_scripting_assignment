import random

def cmp(a):
	return a[0]

f = open("config.txt")
lis = list(f.readline().strip().split(':'))
ov_l, ov_u = int(lis[1]), int(lis[2])
lis = list(f.readline().strip().split(':'))
bow_l, bow_u = int(lis[1]), int(lis[2])
lis = list(f.readline().strip().split(':'))
bat_l, bat_u = int(lis[1]), int(lis[2])
lis = list(f.readline().strip().split(':'))
wick_l, wick_u = int(lis[1]), int(lis[2])
lis = list(f.readline().strip().split(':'))
all_l, all_u = int(lis[1]), int(lis[2])


lis = list(f.readline().strip().split(':'))
teams = int(lis[1])
f.readline()
teams_list = []
for count in range(teams):
	teams_list.append(f.readline().strip())
f.close()

final = {}
for i in range(teams):
	final[i] = []


batsmen = []
bowlers = []
wicket_k = []
all_r = []
overseas = []
player_map = {}
included = {}

f = open("ipl_auctions_dataset.txt")
for line in f.readlines():
	lis = list(line.strip().split(':'))
	player, country, ability, cost = lis[0], lis[1], lis[2], int(lis[3])
	included[player] = False
	if player_map.get(player) == None:
		player_map[player] = []
		player_map[player].append((ability, country, cost))
		if ability == "Batsman":
			batsmen.append(player)
		elif ability == "All-Rounder":
			all_r.append(player)
		elif ability == "Wicket Keeper":
			wicket_k.append(player)
		elif ability == "Bowler":
			bowlers.append(player)
		if country != "India":
			overseas.append(player)
	else:
		repeat = False
		for ind in range(len(player_map[player])):
			lis_tup = player_map[player][ind]
			if lis_tup[0] == ability:
				repeat = True
				player_map[player][ind] = (ability, country, max(lis_tup[2], cost))
				break
		if repeat == False:
			player_map[player].append((ability, country, cost))
			if ability == "Batsman":
				batsmen.append(player)
			elif ability == "All-Rounder":
				all_r.append(player)
			elif ability == "Wicket Keeper":
				wicket_k.append(player)
			elif ability == "Bowler":
				bowlers.append(player)
			if country != "India" and player not in overseas:
				overseas.append(player)

f.close()


print("Batsmen "+str(len(batsmen)))
print("Bowlers "+str(len(bowlers)))
print("Wicket keepers "+str(len(wicket_k)))
print("All rounders "+str(len(all_r)))
print("Overseas "+str(len(overseas)))
print("Total players :" + str(len(player_map.keys())))

random.shuffle(batsmen)
random.shuffle(bowlers)
random.shuffle(wicket_k)
random.shuffle(all_r)

'''
print("Player map")
print(player_map)
print("Batsmen")
print(batsmen)

print(overseas)
print("All rounder")
print(all_r)
print("Wicket K")
print(wicket_k)
print("bowler")
print(bowlers)
print(included)
'''

min_req = [bat_l, bow_l, wick_l, all_l, ov_l]
max_req = [bat_u, bow_u, wick_u, all_u, ov_u]
team_tracker = [[0 for i in range(6)] for j in range(teams)]
ability_map = {"Batsman":0, "Bowler":1, "Wicket Keeper":2, "All-Rounder":3, "Overseas":4}
rev_ability_map = {0:"Batsman", 1:"Bowler", 2:"Wicket Keeper", 3:"All-Rounder", 4:"Overseas"}

# print()
# for row in team_tracker:
# 	print(row)
# print()

players_per_team = 18

for team_no in range(len(team_tracker)):

	
	# print("assignning to team "+str(team_no+1))

	i = 0
	while team_tracker[team_no][4] < ov_l:
		cp = overseas[i]
		if included[cp] == True:
			i += 1
			continue
		num_abs = len(player_map[cp])
		diff_lis = []
		for tup in player_map[cp]:
			ind = ability_map[tup[0]]
			diff_lis.append((team_tracker[team_no][ind]-min_req[ind], ind))
		nl = sorted(diff_lis, key = cmp)
		include = False
		for tup in nl:
			if team_tracker[team_no][tup[1]] + 1 <= max_req[tup[1]] :
				include = True
				team_tracker[team_no][tup[1]] += 1
				team_tracker[team_no][4] += 1
				team_tracker[team_no][5] += 1
				included[cp] = True
				for t in player_map[cp]:
					if t[0] == rev_ability_map[tup[1]]:
						cost = t[2]
				final[team_no].append((cp, (rev_ability_map[tup[1]], player_map[cp][0][1], cost)))
				del overseas[i]
				break
		if include == False:
			i += 1
			continue
	# print("assigned overseas")

	i = 0
	while team_tracker[team_no][3] < all_l:
		cp = all_r[i]
		if included[cp] == True:
			i += 1
			continue
		if cp in overseas and team_tracker[team_no][4] >= ov_u:
			i += 1
			continue
		team_tracker[team_no][3] += 1
		team_tracker[team_no][5] += 1
		if cp in overseas:
			team_tracker[team_no][4] += 1
		included[cp] = True
		for t in player_map[cp]:
			if t[0] == "All-Rounder":
				country = t[1]
				cost = t[2]
		final[team_no].append((cp, ("All-Rounder", country, cost)))
		del all_r[i]
	# print("assigned all rounders")


	i = 0
	while team_tracker[team_no][2] < wick_l:
		cp = wicket_k[i]
		if included[cp] == True:
			i += 1
			continue
		if cp in overseas and team_tracker[team_no][4] >= ov_u:
			i += 1
			continue
		team_tracker[team_no][2] += 1
		team_tracker[team_no][5] += 1
		if cp in overseas:
			team_tracker[team_no][4] += 1
		included[cp] = True
		for t in player_map[cp]:
			if t[0] == "Wicket Keeper":
				country = t[1]
				cost = t[2]
		final[team_no].append((cp, ("Wicket Keeper", country, cost)))
		del wicket_k[i]
	# print("assigned Wicket Keepers")


	i = 0
	while team_tracker[team_no][1] < bow_l:
		cp = bowlers[i]
		if included[cp] == True:
			i += 1
			continue
		if cp in overseas and team_tracker[team_no][4] >= ov_u:
			i += 1
			continue
		team_tracker[team_no][1] += 1
		team_tracker[team_no][5] += 1
		if cp in overseas:
			team_tracker[team_no][4] += 1
		included[cp] = True
		for t in player_map[cp]:
			if t[0] == "Bowler":
				country = t[1]
				cost = t[2]
		final[team_no].append((cp, ("Bowler", country, cost)))
		del bowlers[i]
	# print("assigned bowlers")


	i = 0
	while team_tracker[team_no][0] < bat_l:
		cp = batsmen[i]
		if included[cp] == True:
			i += 1
			continue
		if cp in overseas and team_tracker[team_no][4] >= ov_u:
			i += 1
			continue
		team_tracker[team_no][0] += 1
		team_tracker[team_no][5] += 1
		if cp in overseas:
			team_tracker[team_no][4] += 1
		included[cp] = True
		for t in player_map[cp]:
			if t[0] == "Batsman":
				country = t[1]
				cost = t[2]
		final[team_no].append((cp, ("Batsman", country, cost)))
		del batsmen[i]
	# print("assigned batsmen\n")


# print()
# for row in team_tracker:
# 	print(row)
# print()

# print(final)

# print("minimum satisfied")

for team_no in range(len(team_tracker)):

	while team_tracker[team_no][5] < players_per_team:
		# print("considering team "+str(team_no+1))

		# for row in team_tracker:
		# 	print(row)
		# print()

		diff_list = []
		for i in range(4):
			diff_list.append((max_req[i] - team_tracker[team_no][i], i))
		nl = sorted(diff_list, key = cmp, reverse = True)
		for ele in nl:

			if team_tracker[team_no][5] == players_per_team:
				break

			if ele[1] == 0 and team_tracker[team_no][0] < bat_u:
				for p in batsmen:
					if included[p] == False:
						if p in overseas and team_tracker[team_no][4] >= ov_u:
							continue
						else:
							included[p] = True
							team_tracker[team_no][5] += 1
							team_tracker[team_no][0] += 1
							for t in player_map[p]:
								if t[0] == "Batsman":
									country = t[1]
									cost = t[2]
							final[team_no].append((p, ("Batsman", country, cost)))
							# print("bat filled")
							break

			# for row in team_tracker:
			# 	print(row)
			# print()
		

			if ele[1] == 1 and team_tracker[team_no][1] < bow_u:
				for p in bowlers:
					if included[p] == False:
						if p in overseas and team_tracker[team_no][4] >= ov_u:
							continue
						else:
							included[p] = True
							team_tracker[team_no][5] += 1
							team_tracker[team_no][1] += 1
							for t in player_map[p]:
								if t[0] == "Bowler":
									country = t[1]
									cost = t[2]
							final[team_no].append((p, ("Bowler", country, cost)))
							# print("bowlers filled")
							break

			# for row in team_tracker:
			# 	print(row)
			# print()

			if ele[1] == 2 and team_tracker[team_no][2] < wick_u:
				for p in wicket_k:
					if included[p] == False:
						if p in overseas and team_tracker[team_no][4] >= ov_u:
							continue
						else:
							included[p] = True
							team_tracker[team_no][5] += 1
							team_tracker[team_no][2] += 1
							for t in player_map[p]:
								if t[0] == "Wicket Keeper":
									country = t[1]
									cost = t[2]
							final[team_no].append((p, ("Wicket Keeper", country, cost)))
							# print("wick_l filled")
							break

			# for row in team_tracker:
			# 	print(row)
			# print()

			if ele[1] == 3 and team_tracker[team_no][3] < all_u:
				for p in all_r:
					if included[p] == False:
						if p in overseas and team_tracker[team_no][4] >= ov_u:
							continue
						else:
							included[p] = True
							team_tracker[team_no][5] += 1
							team_tracker[team_no][3] += 1
							for t in player_map[p]:
								if t[0] == "All-Rounder":
									country = t[1]
									cost = t[2]
							final[team_no].append((p, ("All-Rounder", country, cost)))
							# print("All-Rounder filled")
							break

			# for row in team_tracker:
			# 	print(row)
			# print()

# print(teams_list)
for ind in range(len(teams_list)):
	f = open(teams_list[ind]+".txt", "w")
	f.write("Team :"+teams_list[ind]+'\n'+'\n')
	iter = 1
	for tup in final[ind]:
		pn = tup[0]
		ab = tup[1][0]
		country = tup[1][1]
		fees = tup[1][2]
		f.write("Player "+str(iter)+'\n')
		f.write("Name :"+pn+'\n')
		f.write("Ability :"+ab+'\n')
		f.write("Country :"+country+'\n')
		f.write("Fees :"+str(fees)+'\n'+'\n')
		iter += 1
	f.close()

print("All files created")


		