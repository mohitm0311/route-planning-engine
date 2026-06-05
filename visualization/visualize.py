import json
import folium

with open("visualization/route.geojson", "r") as file:
    geojson = json.load(file)

coordinates = geojson["features"][0]["geometry"]["coordinates"]

center_lat = coordinates[0][1]
center_lon = coordinates[0][0]

m = folium.Map(
    location=[center_lat, center_lon],
    zoom_start=18
)

route_points = []

for lon, lat in coordinates:
    route_points.append([lat, lon])

folium.PolyLine(
    route_points,
    
    weight=5
).add_to(m)

folium.Marker(
    route_points[0],
    popup="Start"
).add_to(m)

folium.Marker(
    route_points[-1],
    popup="Destination"
).add_to(m)

m.save("visualization/route.html")

print("Map saved to visualization/route.html")