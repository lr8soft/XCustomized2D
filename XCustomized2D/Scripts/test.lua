require("Scripts.XCustomizedEnum")

GameObject = {
    renderHandle = "",
    textureData = {
        "tex", "Assets/Texture/decision.png"
    },
    angle = 0,
    screenRate = 0,

    projectionMatrix = nil,
    viewMatrix = nil
}

function GameObject.OnInit()
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

    GameObject.renderHandle = XCustomizedRenderer.CreateRenderBatch(
        "STATIC_DRAW", indices, vertices, vertexFormats, elementLength, elementSize, false)
    print("uuid:", GameObject.renderHandle)

    height, width = XCustomizedEngine.GetScreenSize()
    GameObject.screenRate = height / width
    print("Screen height", height, "width:", width)

    GameObject.projectionMatrix = XCustomizedMath.CreateProjectionMatrix(45.0, GameObject.screenRate, 0.1, 100.0)
    GameObject.viewMatrix = XCustomizedMath.CreateViewMatrix({0.0, 0.0, 0.5}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0})
    --get render uuid

    XCustomizedRenderer.UpdateSetting(RenderFunctionID.BLEND, true)
    XCustomizedRenderer.UpdateBlendSettting(BlendFunctionID.SRC_ALPHA, BlendFunctionValue.ONE_MINUS_SRC_ALPHA)
    --update blend settings
end

function GameObject.OnRender()
    local uniformData = {}  --init uniform data

    local modelMatrix = XCustomizedMath.CreateMatrix()

    modelMatrix:Scale({0.5, 0.5, 0.5})
    modelMatrix:Rotate(GameObject.angle, {0, 0, 1})
    modelMatrix:Translate({0.0, 0.0, -3.0})

    table.insert(uniformData, "model")
    table.insert(uniformData, modelMatrix)  -- set model matrix

    table.insert(uniformData, "view")   --set view matrix
    table.insert(uniformData, GameObject.viewMatrix) 

    table.insert(uniformData, "projection")
    table.insert(uniformData, GameObject.projectionMatrix)  -- set projection matrix

    GameObject.angle = GameObject.angle + 5

    XCustomizedRenderer.RenderBatch(GameObject.renderHandle, "Test", "Default", GameObject.textureData, uniformData, 6, 0, {})
end

