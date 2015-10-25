#API List

## Graphic
### LoadGraphic(filename) *
filenameで指定された画像データを読み込む
### DeleteGraphic(filename) 
filenameで指定された画像データを破棄する
### SetTexture(filename) *
filenameで指定された画像データをテクスチャに設定する
### SetGraphicRect(sx,sy,dx,dy) *
左上,右下のテクスチャ座標で指定された長方形の描画範囲を設定する
### SetGraphicAngle(angle)
グラフィックをangle度回転させる
### DrawGraphic(x,y) *
指定されたスクリーン座標を中心として描画する

## Status
### SetCollisionA
### SetInitialBombCount(count) [プレイヤーのみ]
初期のボム数を設定する
### SetItemCollectLine(y) [プレイヤーのみ]
アイテム回収ライン(y軸)
### SetGrazeCircle(r) [プレイヤーのみ]
かすり判定の半径r
### SetIntersectionCircle(x,y,r) [プレイヤーのみ]
当たり判定の中心座標(x,y)と半径r
### SetSpeed(speed) *
スピードを設定する
### SetLife(life) *
体力を設定する
### SetX(x) *
x座標を設定する
### SetY(y) *
y座標を設定する
### GetPlayerX() [プレイヤーのみ]*
プレイヤーのx座標を取得する
### GetPlayerY() [プレイヤーのみ]*
プレイヤーのy座標を取得する
### GetSpeedX() *
x方向の速さdxを取得する
### GetSpeedY() *
y方向の速さdyを取得する
### GetX() *
現在のx座標を取得する
### GetY() *
現在のx座標を取得する
### GetCenterX() *
マップの中心座標xを取得する
### GetCenterY() *
マップの中心座標yを取得する


## Danmaku
### CreatePlayerShot01(x,y,speed,angle,damage,pene,id) ［プレイヤーのみ] -
座標(x,y)から速度speed,角度angle,貫通力peneの弾(id値で指定)を1発打つ
### CreateShot01(x,y,speed,angle,color,delay) *
座標(x,y)から速度speed,角度angleの弾を1発打つ
colorは弾の色,delayは初弾が発射されるまでの遅延フレーム数

## SpellCard
### CutIn(name,img,x1,y1,x2,y2)
ラベルnameのカットインを表示する
imgは表示画像,(x1,y1)(x2,y2)は描画元矩形

## Action
### SetMovePosition02(x,y,frame) *
座標(x,y)にframeフレームかけて移動する

## Keyboard 
### GetKeyState(key) *
指定したキーのステータスを返す
(KEY_PUSH,KEY_HOLD)
## Other
### GetCurrentScriptDirectory() *
現在のディレクトリパスを取得する

