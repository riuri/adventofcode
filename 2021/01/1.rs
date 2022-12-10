use std::io;

fn main() {
    let mut line = String::new();
    io::stdin().read_line(&mut line).expect("EOF");
    let mut last: i32 = line.trim().parse().expect("int");
    let mut count: i32 = 0;
    loop {
        line = String::new();
        io::stdin().read_line(&mut line).expect("EOF");
        let cur: i32 = match line.trim().parse() {
            Ok(r) => r,
            Err(_) => break,
        };
        if cur > last {
            count = count + 1;
        }
        last = cur;
    }
    println!("{}", count);
}
