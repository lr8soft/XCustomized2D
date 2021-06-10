require("XCustomizedMath")
GameObject = {}

function GameObject.TestFunc()
    local matrix = XCustomizedMath.CreateMatrix()

    print("Init Matrix")
    matrix:Show()

    print("Scale 0.5 0.5 0.5")
    matrix:Scale({0.5, 0.5, 0.5})
    matrix:Show()


    print("Rotate 90 degrees, X Axis")
    matrix:Rotate(90, {1, 0, 0})
    matrix:Show()

    print("Translate to 1.0 1.0 1.0")
    matrix:Translate({1.0, 1.0, 1.0})
    matrix:Show()

end