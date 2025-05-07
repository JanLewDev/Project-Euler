fn number_of_divisors(n: &u64) -> usize {
    let sq = n.isqrt();
    if *n == sq * sq {
        return (1..=sq).filter(|i| n % i == 0).count() * 2 - 1;
    }
    return (1..=sq).filter(|i| n % i == 0).count() * 2;
}

fn solve(n: usize) -> u64 {
    let mut i = 1;
    let mut num = 0;
    loop {
        num += i;
        if number_of_divisors(&num) > n {
            return num;
        }
        i += 1;
        println!("{}", num);
    }
}

fn main() {
    println!("{}", solve(500));
}

#[cfg(test)]
mod tests {
    #[test]
    fn triangle_number_500_divisors() {
        assert_eq!(76576500, super::solve(500));
    }
}
