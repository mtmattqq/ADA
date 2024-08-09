use proconio::input;

fn main() {
    input! {
        n: usize,
        edges: [(usize, usize); n - 1]
    }
    let mut g: Vec<Vec<usize>> = vec![Vec::new(); n];
    for (u, v) in edges {
        g[u - 1].push(v - 1);
        g[v - 1].push(u - 1);
    }
    let mut ans: Vec<usize> = vec![0; n];
    let mut sz: Vec<usize> = vec![1; n];
    find_dis(&g, &mut sz, &mut ans, 0, 0, 0);
    find_total_dis(&g, &sz, &mut ans, 0, 0);
    for e in ans {
        println!("{}", e);
    }
}

fn find_dis(g: &Vec<Vec<usize>>, sz: &mut Vec<usize>, ans: &mut Vec<usize>, now: usize, parent: usize, distance: usize) {
    ans[0] += distance;
    for next in &g[now] {
        if *next != parent {
            find_dis(g, sz, ans, *next, now, distance + 1);
            sz[now] += sz[*next];
        }
    }
}

fn find_total_dis(g: &Vec<Vec<usize>>, sz: &Vec<usize>, ans: &mut Vec<usize>, now: usize, parent: usize) {
    for next in &g[now] {
        if *next != parent {
            ans[*next] = ans[now] + g.len() - 2 * sz[*next];
            find_total_dis(g, sz, ans, *next, now);
        }
    }
}