class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int n = classroom.size();
        int m = classroom[0].size();

        int sr = -1, sc = -1;
        vector<pair<int, int>> litter;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } 
                else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        int totalMask = (1 << k) - 1;

        // Give every litter cell a bit number
        vector<vector<int>> id(n, vector<int>(m, -1));

        for (int i = 0; i < k; i++) {
            id[litter[i].first][litter[i].second] = i;
        }

        /*
            maxEnergy[r][c][mask] =
            maximum energy with which we have reached
            (r, c) after collecting 'mask' litter.
        */

        vector<vector<vector<int>>> maxEnergy(
            n,
            vector<vector<int>>(
                m,
                vector<int>(1 << k, -1)
            )
        );

        // r, c, mask, energy
        queue<array<int, 4>> q;

        maxEnergy[sr][sc][0] = energy;
        q.push({sr, sc, 0, energy});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        int moves = 0;

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == totalMask)
                    return moves;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    // One energy is consumed for every move
                    int ne = e - 1;

                    if (ne < 0)
                        continue;

                    int nmask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        nmask |= (1 << id[nr][nc]);
                    }

                    // Recharge
                    if (classroom[nr][nc] == 'R') {
                        ne = energy;
                    }

                    /*
                        If we've already reached this exact
                        position + mask with >= energy,
                        this state is useless.
                    */
                    if (ne <= maxEnergy[nr][nc][nmask])
                        continue;

                    maxEnergy[nr][nc][nmask] = ne;

                    q.push({nr, nc, nmask, ne});
                }
            }

            moves++;
        }

        return -1;
    }
};