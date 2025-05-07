fn collatz_seq_length(n: u64) -> u64 {
    let mut steps = 0;
    let mut curr = n;
    while curr != 1 {
        if curr % 2 == 0 {
            curr /= 2;
        } else {
            curr = 3 * curr + 1;
        }
        steps += 1;
    }
    steps
}

fn solve(limit: u64) -> u64 {
    let mut max_length = 0;
    let mut max_num = 0;
    for i in 1..limit {
        let length = collatz_seq_length(i);
        if length > max_length {
            max_length = length;
            max_num = i;
        }
    }
    max_num
}

fn main() {
    println!("{}", solve(1000000));
}

#[cfg(test)]
mod tests {
    #[test]
    fn longest_collatz_sequence() {
        assert_eq!(837799, super::solve(1000000));
    }
}
