# Give CodeBoot acces to blinx

Codeboot, can't communicate with blinx because of the mixed content: codeboot is in https and blinx in http.

So we need to change a parameter in the browser (the browser need to be Chromium-based) :

1. go to [https://codeboot.org/](https://codeboot.org/)
2. click on the setting button on the left of the navigation bar : ![step 2](<img/step2.png>)
3. Then on the `Site setting` button : ![alt text](<img/step3.png>)
4. Then find the parameter call `Insecure content`. By default, it would be on `Block (default)`, you need to put it on `allow` : ![alt text](<img/step4.png>)
5. Resfresh the CodeBoot page.