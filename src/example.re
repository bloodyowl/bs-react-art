let path = ReactArt.Path.(make () |> moveTo x::0 y::0 |> lineTo x::10 y::10 |> close);

let transform = ReactArt.Transform.(make () |> scale x::2 y::2);

module Demo = {
  type state =
    | Hovered
    | Idle;
  let component = ReasonReact.statefulComponent "Demo";
  let make _children => {
    ...component,
    initialState: fun () => Idle,
    render: fun {state, update} =>
      <ReactArt.Surface width=500 height=500>
        <ReactArt.Rectangle
          x=50
          y=50
          radius=10
          fill=(
            switch state {
            | Hovered =>
              LinearGradient (
                ReactArt.LinearGradient.make
                  stops::[("0.5", "#0f0"), ("1", "#00f")] x1::0 x2::100 y1::0 y2::200
              )
            | Idle => String "#f00"
            }
          )
          width=100
          height=200
          scale=(
            switch state {
            | Hovered => 1.2
            | Idle => 1.0
            }
          )
          onMouseOver=(update (fun _ _ => ReasonReact.Update Hovered))
          onMouseOut=(update (fun _ _ => ReasonReact.Update Idle))
        />
        <ReactArt.Wedge
          x=100
          y=300
          outerRadius=100
          startAngle=0
          endAngle=130
          innerRadius=80
          fill=(
            LinearGradient (
              ReactArt.LinearGradient.make
                stops::[("0.5", "#ccc"), ("1", "#333")] x1::0 x2::100 y1::0 y2::200
            )
          )
        />
        <ReactArt.Circle
          x=300
          y=100
          radius=50
          fill=(
            RadialGradient (
              ReactArt.RadialGradient.make
                stops::[("0", "#fb5"), ("0.5", "#ea6"), ("1", "#fff")] fx::0 fy::0 rx::50 ry::50 cx::0 cy::0
            )
          )
          stroke="rgba(0, 0, 0, 0.3)"
          strokeWidth=2
        />
      </ReactArt.Surface>
  };
};

ReactDOMRe.renderToElementWithId <Demo /> "root";
