package db

import (
	"graphql-samples/utils"

	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
)

func New() *gorm.DB {
	db, err := gorm.Open(sqlite.Open("gorm.db"), &gorm.Config{})
	utils.UnwrapError(err)

	err = db.AutoMigrate(&User{}, &Todo{})
	utils.UnwrapError(err)

	return db
}
