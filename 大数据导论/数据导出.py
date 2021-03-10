import pandas as pd
hands = pd.read_json('C:\Users\DELL\Desktop\skinData\Skins\hands.json',encoding='utf-8')
#hands.head(5)
handsOrder = pd.read_json('C:\Users\DELL\Desktop\skinData\sell_order\handsOrder.json')
hands.to_csv('C:\Users\DELL\Desktop\skinData\Skins\hands.csv')
handsOrder.to_csv('C:\Users\DELL\Desktop\skinData\sell_order\handsOrder.csv')