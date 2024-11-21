package db

import "gorm.io/gorm"

type User struct {
	gorm.Model
	ID   uint `gorm:"primaryKey;autoIncrement"`
	Name string
}

type Todo struct {
	gorm.Model
	ID     uint `gorm:"primaryKey;autoIncrement"`
	Text   string
	Done   bool
	UserID uint
	User   User `gorm:"foreignKey:UserID"`
}
