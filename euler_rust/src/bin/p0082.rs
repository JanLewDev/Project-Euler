use std::{
    fs::File,
    io::{self, BufRead, BufReader},
};

fn read_matrix(filename: &str) -> Result<Vec<Vec<u32>>, io::Error> {
    let mut matrix = vec![];

    // read lines
    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    for line in reader.lines() {
        match line {
            Ok(line) => {
                let row: Vec<u32> = line.split(",").map(|s| s.parse().unwrap()).collect();
                matrix.push(row);
            }
            Err(e) => return Err(e),
        }
    }

    Ok(matrix)
}

fn solve(filename: &str) -> u32 {
    let matrix = read_matrix(filename).unwrap();

    let (n, m) = (matrix.len(), matrix[0].len()); // height, width

    let mut dp = vec![vec![0; m]; n];

    for i in 0..n {
        dp[i][0] = matrix[i][0];
    }

    for j in 1..m {
        for i in 0..n {
            let mut min = dp[i][j - 1];

            let mut sum = 0;
            for di in 1..i {
                sum += matrix[i - di][j];
                min = min.min(dp[i - di][j - 1] + sum);
            }

            sum = 0;
            for di in 1..n - i {
                sum += matrix[i + di][j];
                min = min.min(dp[i + di][j - 1] + sum);
            }

            dp[i][j] = matrix[i][j] + min;
        }
    }

    dp.iter()
        .map(|row| row.last().unwrap())
        .min()
        .unwrap()
        .to_owned()
}

fn main() {
    println!("{}", solve("./input/0082_matrix.txt"));
}

#[cfg(test)]
mod tests {
    #[test]
    fn path_sum_three_ways() {
        assert_eq!(260324, super::solve("./input/0082_matrix.txt"));
    }
}
