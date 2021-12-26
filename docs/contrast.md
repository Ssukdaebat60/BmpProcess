## Change Contrast by Multiplying Same Value
```c
void contrast(float num, bool overwrite = true){
	if (overwrite)
		multipleWith(B, G, R, num, num, num);
	else
		multipleWith(rawB, rawG, rawR, num, num, num);
}
```
## Contrast Increase(vivid)
```c
contrast(1.2);
```

## Contrast Decrease(blurry)
```c
contrast(0.8)
```
