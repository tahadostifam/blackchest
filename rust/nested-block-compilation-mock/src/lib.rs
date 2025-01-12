type BlockID = i32;

#[derive(Clone)]
struct Block  {
    block_id: BlockID,
    parent: Option<Box<Block>>,
}

impl Block {
    fn jump(&self) {
        if let Some(parent) = &self.parent {
            println!("jumping to block id: {}", parent.block_id);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_blocks() {
        let parent = Block { block_id: 1, parent: None };
        let child1 = Block { block_id: 2, parent: Some(Box::new(parent.clone())) };

        child1.jump();
        // parent.jump();
    }
}
