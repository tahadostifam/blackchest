package utils

import "log"

func UnwrapError(err error) {
	if err != nil {
		log.Fatalln(err)
	}
}
