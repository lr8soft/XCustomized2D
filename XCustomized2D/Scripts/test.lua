require("XCustomizedMath")
require("XCustomizedRenderer")
require("XCustomizedEngine")

GameObject = {
    renderHandle = "",
    textureData = {
        "tex", "Assets/Texture/test.png"
    },
    angle = 0
}

function GameObject.TestFunc()
    local vertices = {
        1.0, 1.0,
        1.0,-1.0,
       -1.0,-1.0,
       -1.0, 1.0
    }
   
    local indices = {0, 1, 2, 2, 3, 0}
    local vertexFormats = {0}   --no need format
	local elementLength = {2}
	local elementSize = {0}

    GameObject.renderHandle = XCustomizedRenderer.CreateRenderBatch("STATIC_DRAW", indices, vertices, vertexFormats, elementLength, elementSize, false)
    print("uuid:", GameObject.renderHandle)

    height, width = XCustomizedEngine.GetScreenSize()
    print("Screen height", height, "width:", width)
    --get render uuid
end

function GameObject.OnRender()
    local uniformData = {}  --init uniform data

    local matrix = XCustomizedMath.CreateMatrix()

    matrix:Scale({0.5, 0.5, 0.5})
    matrix:Rotate(GameObject.angle, {0, 0, 1})

    table.insert(uniformData, "mvp_mat")
    table.insert(uniformData, matrix)  -- mvp_mat--->matrix

    GameObject.angle = GameObject.angle + 1
    if GameObject.angle > 360 then
        GameObject.angle = 0
    end

    XCustomizedRenderer.RenderBatch(GameObject.renderHandle, "Test", "Default", GameObject.textureData, uniformData, 6, 0, {})
end

