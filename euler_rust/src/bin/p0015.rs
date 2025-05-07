fn solve(n: usize, m: usize) -> u64 {
    let mut dp = vec![vec![0; m + 1]; n + 1];
    for i in 0..=n {
        dp[i][0] = 1;
    }
    for i in 0..=m {
        dp[0][i] = 1;
    }
    for i in 1..=n {
        for j in 1..=m {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    dp[n][m]
}

fn main() {
    println!("{}", solve(20, 20));
}

#[cfg(test)]
mod tests {
    #[test]
    fn lattice_paths() {
        assert_eq!(137846528820, super::solve(20, 20));
    }
}
