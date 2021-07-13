# Machine_Learning

## 소개   

이 프로젝트는
  - 신인우   
  - 박지원   
   
을 조원으로 한 머신러닝 프로젝트이다.

   
## 구조

![뉴런](https://user-images.githubusercontent.com/59462895/125373224-b0d5ea80-e3bf-11eb-9815-716b716b11a9.png)
   
   히든 레이어는 총 1 ~ 10 개의 레이어까지 로 구현하였다.   
   각 레이어에 조정할 수 있는 뉴런은 input 은 10개 Hidden Layer 의 경우에는 15 개까지 설정할 수 있도록 하였다. 그리고 아웃풋은 2개로 설정하였다. 추가적으로 바이어스를 연결할 것인지 안연결할 것인지 설정할 수도 있다.   
      
## 플로우 차트   

![다이어그램](https://user-images.githubusercontent.com/59462895/125373528-46717a00-e3c0-11eb-8121-b4d072da27ce.png)

위와 같은 플로우 차트의 구조로 만들었다. 왼쪽의 노란 박스는 격자 테스트를 수행하는 함수에 대한 부분 부분이다. 그리고 Error Back Propagation 알고리즘을 구현한 부분은 오른쪽 파란박스에 대한 구간이다.   

## 학습 데이터   
학습 데이터로는,
 - Training Data   

![네잎클로버_모양](https://user-images.githubusercontent.com/59462895/125374105-445beb00-e3c1-11eb-9a3e-949a654498b9.png)   
학습데이터는 다음과 같은 것을 사용하였다. 네잎클로버 모양으로 선을 파이썬 코드로 그었다. 그리고 그 선을 기준으로 안은 좌표값과 1의 값, 밖은 좌표값과 0의 값을 출력하는 파이썬 코드로 점을 찍어서 데이터를 추출하였다.

 - Evaluation Data    
  
<img width="417" alt="이밸류데이터" src="https://user-images.githubusercontent.com/59462895/125374235-900e9480-e3c1-11eb-9001-3618ab435ce7.png">   

다음과 같은 Evaluation data 를 학습이 잘 수행되었는지를 알아보기 위해서 사용하였다.

## 결과    
![평균](https://user-images.githubusercontent.com/59462895/125374514-204cd980-e3c2-11eb-9e3d-051386d1a8a1.png)   
각각 에러는 위의 공식을 사용하여 기댓값과 원하고자 하는 값의 차이를 모든 Epoch 의 것을 다 더해서 백분율로 나타낸 값이다.   

### Error   
-  Eta = 0.9   

![Error_바이어스](https://user-images.githubusercontent.com/59462895/125374442-fdbac080-e3c1-11eb-83cc-90eab7c6c015.png)   

- Eta = 0.125    

![Eta_0 125_Error](https://user-images.githubusercontent.com/59462895/125374722-8b96ab80-e3c2-11eb-871c-f76c79008cce.png)   

### Evaluation Test Error   
 - Eta = 0.9   

![Eva_Error_바이어스](https://user-images.githubusercontent.com/59462895/125374858-e16b5380-e3c2-11eb-9081-3bd751867728.png)

- Eta = 0.125    

![Eta_0 125_Eva](https://user-images.githubusercontent.com/59462895/125374790-b254e200-e3c2-11eb-885e-f58f29fc7cf9.png)   

### 격자 테스트   
 #### Eta = 0.9
  - 3 Layer 

![레이어3](https://user-images.githubusercontent.com/59462895/125374939-19729680-e3c3-11eb-9ab1-52ca4721ea82.png)   

 - 5 Layer   

 ![레이어5](https://user-images.githubusercontent.com/59462895/125375048-46bf4480-e3c3-11eb-9dbd-ab83244b04fb.png)

 - 10 Layer   

![레이어10](https://user-images.githubusercontent.com/59462895/125375091-59d21480-e3c3-11eb-9562-ce054a3ae38c.png)   

 #### Eta = 0.125   
 - Layer 3   

 ![Eta_0 125_레이어3](https://user-images.githubusercontent.com/59462895/125388072-d112a300-e3d9-11eb-941c-c74f873ce03e.png)

  - Layer 5   

![Eta_0 125_레이어5](https://user-images.githubusercontent.com/59462895/125388079-d2dc6680-e3d9-11eb-87b6-297718ed94af.png)   

   - Layer 10   

![Eta_0 125_레이어10](https://user-images.githubusercontent.com/59462895/125388081-d374fd00-e3d9-11eb-8d75-dca99b0389a7.png)

### 추가적인 테스트    
 - 사람모양 데이터   

![Doraemon_학습](https://user-images.githubusercontent.com/59462895/125388268-2f3f8600-e3da-11eb-92c7-b46b21889dc7.png)   

 - 격자 테스트   

![도라에몽_학습결과](https://user-images.githubusercontent.com/59462895/125388361-54cc8f80-e3da-11eb-8e09-a747b2bbd99b.png)