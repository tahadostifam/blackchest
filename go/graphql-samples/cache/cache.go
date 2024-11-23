package cache

import (
	"context"
	"log"

	"github.com/99designs/gqlgen/graphql"
)

type Cache struct {
	HashTable map[string]interface{}
}

func (c *Cache) Add(ctx context.Context, key string, value string) {
	log.Printf("set [%s]: %v\n", key, value)
	c.HashTable[key] = value
}

func (c *Cache) Get(ctx context.Context, key string) (string, bool) {
	val, ok := c.HashTable[key]
	log.Printf("get [%s]: %v\n", key, val)
	return val.(string), ok
}

func NewCache() graphql.Cache[string] {
	return &Cache{
		HashTable: make(map[string]interface{}),
	}
}
