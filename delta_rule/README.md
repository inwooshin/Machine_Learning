# Delta Rule   

## 소개   
   
![델타룰](https://user-images.githubusercontent.com/59462895/126101812-e202d170-47c9-40e8-b765-978ba582ca31.JPG)   
   
위의 공식을 사용해서 w의 값을 변화시킨다. if then 으로 확인을 하고 연산을 수행하지 않아도 된다.   
   
   그리고 파이썬 코드로 각각 좌표에 대한 and 와 or 의 값을 가시적으로 확인할 수 있도록 만들어두었다.
   
## 목차   
   
  1. [알고리즘](#알고리즘)
  2. [장점](#장점)
  3. [결과](#결과)
  4. [사용법](#사용법)

## 알고리즘   
![net공식](https://user-images.githubusercontent.com/59462895/126088438-d50f45e2-f023-4eb1-b78c-6924ac72ccc4.JPG)   
    
위의 공식을 사용해서 net 의 값을 구하고,   

![if_then_공식](https://user-images.githubusercontent.com/59462895/126087442-b7215a00-503c-4532-b38a-e8b474f941ab.JPG)   
   
위의 그림처럼 임계치를 넘으면 1, 넘지 않으면 0이 되도록 한다. 그리고 그 값을 토대로,

![델타룰](https://user-images.githubusercontent.com/59462895/126101812-e202d170-47c9-40e8-b765-978ba582ca31.JPG)   
   
위의 공식을 사용해서 if then의 과정을 대체하여 w의 값을 변화시킨다.   
   
![에러](https://user-images.githubusercontent.com/59462895/126102927-5ae2a67e-aca5-4b78-a304-e4c39c0f7d78.JPG)   
   
그리고 위의 공식을 사용해서 각각 좌표에 해당하는 곳에 대한 Error 의 값을 구한다.

## 장점   
 - if then 알고리즘과 다르게 if 문으로 확인하지 않아도 되어서 코드가 훨씬 간결하다.
 - 여러 줄의 코드를 작성하지 않고 한줄로 대체되어서 훨씬 빠르다.
 - Error 의 값을 확인할 수 있다.

## 결과   
 - w1, w2, Error   

![사선](https://user-images.githubusercontent.com/59462895/126103194-a408d7b0-93fb-4cb9-bf97-00fda5e38a48.JPG)   

 - w2, Error   

![error_w2](https://user-images.githubusercontent.com/59462895/126103203-792b82ce-9cd0-496e-9ef9-dc9975b9e1db.JPG)   

 - w1, w2   

![w1_w2](https://user-images.githubusercontent.com/59462895/126103205-c7ef09a9-8ea7-4881-b693-3c456a380f36.JPG)

 - w1, Error   

![Error_w1](https://user-images.githubusercontent.com/59462895/126103209-834a05ee-d040-46fb-8da3-1788794f5764.JPG)   
   
격자테스트를 수행하였을때, 각각의 좌표에서 다음과 같은 값을 보이고 있다. 

## 사용법   

이번 파이썬으로 만드는 그래프의 경우에는 3d 로 그리기 때문에 더욱더 디테일한 확인을 쉽게 하기위해서 시점을 바꾸는 기능을 추가하였다. 그래프 밖에서 밑의 동작을 수행하면 해당기능을 한다.    
해당 파일은 [and_or_cmp_view_change](./and_or_cmp_view_change.py) 이다.
   
 - 마우스 왼쪽 클릭 - w2, Error 좌표 방향으로 보기
 - 마우스 휠 클릭 - w1, w2 좌표 방향으로 보기
 - 마우스 오른쪽 클릭 - w1, Error 좌표 방향으로 보기