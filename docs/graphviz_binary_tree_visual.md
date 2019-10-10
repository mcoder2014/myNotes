# 绘制一棵二叉树

## 一般二叉树可视化
```Rust
pub fn print_dot<T: PartialOrd + Display>(tree: &AvlTreeNode<T>) {
    fn print_node<T: PartialOrd + Display>(node: &Box<TreeNode<T>>) {
        let mut target = None;
        let mut distance = 0;

        if let Some(x) = &node.left {
            let mut left_max = x;
            let mut left_distance = 1;
            loop {
                if let Some(x) = &left_max.right {
                    left_max = x;
                    left_distance += 1;
                } else {
                    break;
                }
            }
            target = Some(&left_max.val);
            distance = left_distance;

            if x.left.is_some() || x.right.is_some() {
                println!("    {} [group={}]", x.val, x.val);
            }
            println!("    {} -> {}", node.val, x.val);
            print_node(x);
        }

        if node.left.is_some() || node.right.is_some() {
            println!(
                "    _{} [group={}, label=\"\", width=0, style=invis]",
                node.val, node.val
            );
            println!("    {} -> _{} [style=invis]", node.val, node.val);
        }

        if let Some(x) = &node.right {
            let mut right_min = x;
            let mut right_distance = 1;
            loop {
                if let Some(x) = &right_min.left {
                    right_min = x;
                    right_distance += 1;
                } else {
                    break;
                }
            }
            if !(right_distance > distance) {
                target = Some(&right_min.val);
                distance = right_distance;
            }

            if x.left.is_some() || x.right.is_some() {
                println!("    {} [group={}]", x.val, x.val);
            }
            println!("    {} -> {}", node.val, x.val);
            print_node(x);
        }

        if distance > 1 {
            if let Some(x) = target {
                println!("    {{rank=same; _{}; {}}}", node.val, x);
            }
        }
    }

    if let Some(x) = tree {
        println!("digraph G {{");
        println!("    graph [nodesep=0.1]");
        println!("    node [shape=circle]");
        println!("    edge [arrowhead=vee]");
        if x.left.is_some() || x.right.is_some() {
            println!("    {} [group={}]", x.val, x.val);
        }
        print_node(x);
        println!("}}");
    }
}
```


# Reference
1. [Graphviz](http://www.graphviz.org/)
2. [用 Graphviz 绘制一棵漂亮的二叉树](https://blog.nanpuyue.com/2019/054.html)